#include <cstdlib>
#include <filesystem>
#include <iostream>
#include <string>

namespace fs = std::filesystem;

namespace {

std::string quote_for_shell(const std::string &value) {
    std::string out = "'";
    for (char c : value) {
        if (c == '\'') {
            out += "'\\''";
        } else {
            out += c;
        }
    }
    out += "'";
    return out;
}

bool run_command(const std::string &cmd) {
    return std::system(cmd.c_str()) == 0;
}

bool create_zip_archive(const fs::path &archive_path, const fs::path &input) {
    std::string cmd;

#if defined(_WIN32)
    cmd = "powershell -NoProfile -Command \"Compress-Archive -Path " +
          quote_for_shell(input.string()) +
          " -DestinationPath " + quote_for_shell(archive_path.string()) +
          " -Force\"";
#else
    cmd = "zip -q -r " + quote_for_shell(archive_path.string()) +
          " " + quote_for_shell(input.string());
#endif

    if (!run_command(cmd)) {
        std::cerr << "Failed to create archive with command:\n  " << cmd << '\n';
        return false;
    }

    return fs::exists(archive_path);
}

bool rename_to_requested_extension(const fs::path &temp_zip, const fs::path &target) {
    try {
        if (fs::exists(target)) {
            fs::remove(target);
        }
        fs::rename(temp_zip, target);
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Failed to rename archive: " << e.what() << '\n';
        return false;
    }
}

} // namespace

int main(int argc, char *argv[]) {
    if (argc < 4 || std::string(argv[1]) != "-f") {
        std::cerr << "Usage: zconvert -f <folder_or_file> [more folders/files] <target_extension>\n";
        return 1;
    }

    const std::string target_ext = std::string(argv[argc - 1]);
    if (target_ext.empty() || target_ext[0] != '.') {
        std::cerr << "Target extension must start with '.': " << target_ext << '\n';
        return 1;
    }

    for (int i = 2; i < argc - 1; ++i) {
        const fs::path input = argv[i];
        if (!fs::exists(input)) {
            std::cerr << "Input does not exist: " << input << '\n';
            return 1;
        }

        const fs::path temp_zip = input.parent_path() / (input.filename().string() + ".zip");
        if (!create_zip_archive(temp_zip, input)) {
            return 1;
        }

        const fs::path output = input.parent_path() /
                               (input.filename().string() + target_ext);
        if (!rename_to_requested_extension(temp_zip, output)) {
            return 1;
        }

        std::cout << "Created archive: " << output << '\n';
    }

    return 0;
}
