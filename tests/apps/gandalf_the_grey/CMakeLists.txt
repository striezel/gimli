# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

# test for no / missing arguments
add_test(NAME gandalf_the_grey_missing_arguments
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/no-arguments.sh $<TARGET_FILE:gandalf-the-grey>)

# test: non-existent file
add_test(NAME gandalf_the_grey_file_does_not_exist
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-does-not-exist.sh $<TARGET_FILE:gandalf-the-grey>)

# test: file type detection fails
add_test(NAME gandalf_the_grey_type_detection_failure
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-type-undetermined.sh $<TARGET_FILE:gandalf-the-grey> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: file type is unknown
add_test(NAME gandalf_the_grey_unknown_file_type
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-type-unknown.sh $<TARGET_FILE:gandalf-the-grey> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: file cannot be loaded
add_test(NAME gandalf_the_grey_fail_to_load
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/fail-to-load.sh $<TARGET_FILE:gandalf-the-grey> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: valid RGB JPEG file
add_test(NAME gandalf_the_grey_valid_jpeg_image
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/valid-file.sh $<TARGET_FILE:gandalf-the-grey> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: valid RGB JPEG file, but destination already exists
add_test(NAME gandalf_the_grey_file_name_with_number
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-name-with-number.sh $<TARGET_FILE:gandalf-the-grey> "${CMAKE_CURRENT_SOURCE_DIR}")
