# We might support earlier versions, too, but try to use a recent one.
cmake_minimum_required (VERSION 3.8)

# test for no / missing arguments
add_test(NAME hobbit_missing_arguments
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/no-arguments.sh $<TARGET_FILE:hobbit>)

# test: non-existent file
add_test(NAME hobbit_does_not_exist
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-does-not-exist.sh $<TARGET_FILE:hobbit>)

# test: file type detection fails
add_test(NAME hobbit_type_detection_failure
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-type-undetermined.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: file type is unknown
add_test(NAME hobbit_unknown_file_type
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/file-type-unknown.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: file cannot be loaded
add_test(NAME hobbit_fail_to_load
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/fail-to-load.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: size not specified
add_test(NAME hobbit_size_not_specified
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/size-not-specified.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: size given twice
add_test(NAME hobbit_size_parameter_given_twice
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/size-given-twice.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: size fails to parse
add_test(NAME hobbit_size_fails_to_parse
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/size-fails-to-parse.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: size parameter without numbers
add_test(NAME hobbit_size_but_no_numbers
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/size-but-no-numbers.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: resize of image fails
add_test(NAME hobbit_resize_failure
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/resize-fail.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: file with name of resized image already exists
add_test(NAME hobbit_target_file_exists
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/target-file-exists.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")

# test: valid RGB JPEG file
add_test(NAME hobbit_valid_jpeg_image
         COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/valid-file.sh $<TARGET_FILE:hobbit> "${CMAKE_CURRENT_SOURCE_DIR}")
