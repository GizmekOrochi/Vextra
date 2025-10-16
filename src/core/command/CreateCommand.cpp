#include "../include/command/CreateCommand.hpp"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

namespace vextra {

void CreateCommand::execute(const std::vector<std::string_view>& args) {
    if (args.empty()) {
        std::cerr << ICON_ERROR << " Missing project name.\nUsage: "
                  << APP_NAME << " create <ProjectName> [-cpp | -c | -java]\n";
        return;
    }

    std::string projectName(args[0]);
    std::string_view language = (args.size() > 1) ? args[1] : DEFAULT_LANGUAGE;

    if (fs::exists(projectName)) {
        std::cerr << ICON_WARNING << " Directory '" << projectName << "' already exists.\n";
        return;
    }

    try {
        createProjectStructure(projectName);
        createBaseFiles(projectName, language);
        std::cout << ICON_SUCCESS << " Project '" << projectName << "' created successfully!\n";
        if (language != DEFAULT_LANGUAGE)
            std::cout << "🧠 Language: " << language << "\n";
    } catch (const std::exception& e) {
        std::cerr << ICON_ERROR << " Failed to create project: " << e.what() << "\n";
    }
}

void CreateCommand::createProjectStructure(const std::string& name) {
    fs::create_directories(name + "/" + std::string(SRC_DIR));
    fs::create_directories(name + "/" + std::string(INCLUDE_DIR));
    fs::create_directories(name + "/" + std::string(CORE_DIR));
    fs::create_directories(name + "/" + std::string(RESOURCE_DIR));
    fs::create_directories(name + "/" + std::string(BIN_DIR));
    fs::create_directories(name + "/" + std::string(DOC_DIR));
    fs::create_directories(name + "/" + std::string(TESTS_DIR));
    fs::create_directories(name + "/" + std::string(LIBS_DIR));
}

void CreateCommand::createBaseFiles(const std::string& name, std::string_view language) {
    const fs::path base = name;

    // README
    std::string readme = std::string(DEFAULT_README);
    size_t pos = readme.find("{project}");
    if (pos != std::string::npos) readme.replace(pos, 9, name);
    createFile(base / "README.md", readme);

    // .gitignore
    createFile(base / ".gitignore", std::string(DEFAULT_GITIGNORE));

    // Metadata
    createFile(base / ("." + name + "-Info"), "# Metadata file for Vextra.\n");

    // Makefile (language-dependent)
    std::string makefile;
    if (language == "-cpp")
        makefile = "CXX = g++\nSRC = $(wildcard src/core/*.cpp)\nOBJ = $(SRC:.cpp=.o)\nBIN = bin/" + name +
                   "\n\n$(BIN): $(OBJ)\n\t$(CXX) $(OBJ) -o $(BIN)\n\nclean:\n\trm -f $(OBJ) $(BIN)\n";
    else if (language == "-c")
        makefile = "CC = gcc\nSRC = $(wildcard src/core/*.c)\nOBJ = $(SRC:.c=.o)\nBIN = bin/" + name +
                   "\n\n$(BIN): $(OBJ)\n\t$(CC) $(OBJ) -o $(BIN)\n\nclean:\n\trm -f $(OBJ) $(BIN)\n";
    else if (language == "-java")
        makefile = "JAVAC = javac\nSRC = $(wildcard src/core/*.java)\nBIN = bin\n\nall:\n\t$(JAVAC) -d $(BIN) $(SRC)\n";
    else
        makefile = "# Empty Makefile (no language specified)\n";

    createFile(base / "src" / "Makefile", makefile);

    // Entry point
    if (language == "-cpp")
        createFile(base / "src/main.cpp", "#include <iostream>\nint main(){ std::cout << \"Hello from " + name + "!\\n\"; }\n");
    else if (language == "-c")
        createFile(base / "src/main.c", "#include <stdio.h>\nint main(){ printf(\"Hello from " + name + "!\\n\"); }\n");
    else if (language == "-java")
        createFile(base / "src/Main.java", "public class Main { public static void main(String[] args){ System.out.println(\"Hello from " + name + "!\"); }}\n");
    else
        createFile(base / "src/main.txt", "# Entry point placeholder.\n");
}

void CreateCommand::createFile(const fs::path& path, const std::string& content) {
    std::ofstream file(path);
    if (!file)
        throw std::runtime_error("Cannot create file: " + path.string());
    file << content;
}

} // namespace vextra
