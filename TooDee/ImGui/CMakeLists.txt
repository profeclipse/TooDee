target_sources(toodee PRIVATE
    ImGuiLayer.cpp
    ImGuiBuild.cpp
    )

target_sources(toodee PUBLIC
    FILE_SET HEADERS
    FILES
    ImGuiLayer.h
    )
