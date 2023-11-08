set(SOURCES
	src/SandboxApp.cpp
    src/ExampleLayer.cpp
	)

add_executable(sandbox
	${SOURCES}
	)

target_link_libraries(sandbox PRIVATE
	toodee::toodee
	)
