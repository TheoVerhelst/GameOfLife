set(SOURCE_FILES
	Grid.cpp
	GameBoard.cpp
	Cell.cpp
	ThreadHelper.cpp
	main.cpp
	)

#Create the main executable
add_executable(${EXECUTABLE_NAME} ${SOURCE_FILES})

#Link external librairies
target_link_libraries(${EXECUTABLE_NAME} ${EXTERNAL_LIBRARIES})
