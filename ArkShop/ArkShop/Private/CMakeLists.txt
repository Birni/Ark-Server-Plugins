cmake_minimum_required (VERSION 3.8)

add_subdirectory(Database)
add_subdirectory(UIHandler)


target_include_directories(${ProjectName}
	PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}
)

set( SOURCE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/ArkShop.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/DBHelper.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/json.hpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Kits.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Points.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/Store.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/StoreSell.cpp
   ${CMAKE_CURRENT_SOURCE_DIR}/TimedRewards.cpp

)
set( HEADE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/ArkShop.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ShopLog.h
   ${CMAKE_CURRENT_SOURCE_DIR}/StoreSell.h
   ${CMAKE_CURRENT_SOURCE_DIR}/TimedRewards.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ArkShopTools.h
)

target_sources(${ProjectName}
    PUBLIC
		${SOURCE_FILES}
	PUBLIC
		${HEADE_FILES}
)

