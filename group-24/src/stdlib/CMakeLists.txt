########################################
###
### UiAOS Module: stdlib
# The standard library for our operating system. It is some mutilated attempt at doing some libc implementation, but we probably void
# all existing standards.
########################################
set(OS_MODULE_STDLIB_NAME ${OS_KERNEL_NAME}-module-stdlib)
set(OS_MODULE_STDLIB_SOURCES
       ./src/system.c
)
add_library(${OS_MODULE_STDLIB_NAME} ${OS_MODULE_STDLIB_SOURCES})

target_link_libraries(${OS_MODULE_STDLIB_NAME}
        ${OS_LIBRARIES}
)

target_include_directories(${OS_MODULE_STDLIB_NAME} PUBLIC
    PUBLIC ${STDLIB_PATH}/include
    .

)

set(OS_LIBRARIES ${OS_LIBRARIES} ${OS_MODULE_STDLIB_NAME})