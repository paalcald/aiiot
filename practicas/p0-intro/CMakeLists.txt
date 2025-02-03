cmake_minimum_required(VERSION 3.5)

# Define the project name
project(monte_carlo)

# Find the Python interpreter, libraries and headers
find_package(Python3 COMPONENTS Interpreter Development REQUIRED)

# Set the module name
set(MODULE_NAME monte_carlo)

# Add the module source file
set(SOURCE_FILE monte_carlo.c)

# Create a Python extension module
Python3_add_library(${MODULE_NAME} MODULE ${SOURCE_FILE})

# Link the Python library using the keyword signature
target_link_libraries(${MODULE_NAME} PRIVATE Python3::Python)
