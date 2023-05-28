########################################
###
### UiAOS Module: stdlib
# The standard library for our operating system. It is some mutilated attempt at doing some libc implementation, but we probably void
# all existing standards.
########################################
set(OS_MODULE_STDLIB_NAME ${OS_KERNEL_NAME}-module-stdlib)
set(OS_MODULE_STDLIB_SOURCES
        ${STDLIB_PATH}/src/system.c
        ${STDLIB_PATH}/src/screen.cpp
)
add_library(${OS_MODULE_STDLIB_NAME} ${OS_MODULE_STDLIB_SOURCES})
target_include_directories(${OS_MODULE_STDLIB_NAME} 
    PUBLIC ${STDLIB_PATH}/include
    .

)
target_link_libraries(${OS_MODULE_STDLIB_NAME} PUBLIC
        ${OS_LIBRARIES}
)
set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_STDLIB_NAME} PARENT_SCOPE)
