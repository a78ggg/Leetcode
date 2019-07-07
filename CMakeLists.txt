project(MIKE_CHANG)
cmake_minimum_required(VERSION 3.2)
Add_Definitions(-DUNICODE -D_UNICODE)
add_definitions("/wd4996")
set_property(GLOBAL PROPERTY USE_FOLDERS On)

set(AllLib
)
set(Leetcode_Main
leetcode.cpp
)
SOURCE_GROUP("Main" FILES ${Leetcode_Main})

set(Leetcode_SRC
functions.cpp
functions.h
)
SOURCE_GROUP("Function" FILES ${Leetcode_SRC})

ADD_EXECUTABLE(LeetCode
${Leetcode_Main}
${Leetcode_SRC}
)

set_target_properties(LeetCode PROPERTIES FOLDER "Application")
target_link_libraries(LeetCode ${AllLib})
INSTALL(TARGETS LeetCode DESTINATION bin)