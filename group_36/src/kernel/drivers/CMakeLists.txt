########################################
###
### OS Module: Monitor
# Module for supporting printing to the display/terminal
###
########################################
add_subdirectory(monitor)

########################################
###
### OS Module: Keyboard
# Module for supporting keyboard events
###
########################################
add_subdirectory(keyboard)

set(OS_LIBRARIES ${OS_LIBRARIES} PARENT_SCOPE)