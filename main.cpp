#include <cstdio>
#include <iostream>
#include <sys/stat.h>
#include <unistd.h>
#define GetCurrentDir getcwd
#include <array>

std::string exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) throw std::runtime_error("popen() failed!");
    while (!feof(pipe.get())) {
        if (fgets(buffer.data(), 128, pipe.get()) != NULL)
            result += buffer.data();
    }
    return result;
}

inline bool is_file_exists (const std::string& name) {
    struct stat buffer;
    return (stat (name.c_str(), &buffer) == 0);
}

std::string GetCurrentWorkingDir( void ) {
    char buff[FILENAME_MAX];
    GetCurrentDir( buff, FILENAME_MAX );
    std::string current_working_dir(buff);
    return current_working_dir;
}

int main() {
    if (is_file_exists(GetCurrentWorkingDir() + "/.git")) {
        std::cout << exec("git commit -am \"Doing work\"") << std::endl;
        std::cout << exec("git push origin master") << std::endl;
        return 0;
    } else {
        std::cerr << "The current directory is not a git repository!" << std::endl;
        return 1;
    }
}