from conans import ConanFile, CMake

class HomeworkRPS(ConanFile):
    generators = "cmake", "cmake_find_package"
    settings = "os", "compiler", "build_type", "arch"
    requires = (
        "cmake/3.22.0",
    )

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
