cmake_minimum_required (VERSION 3.8)

option(TEST "Test" OFF)


project (${ProjectName} )

message(${ProjectName})

set_property(GLOBAL PROPERTY USE_FOLDERS ON)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W3")
SET (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -lglapi")


if(TEST)

enable_testing() 

add_executable(${ProjectName})
target_link_libraries(${ProjectName} gtest_main)

add_test(NAME Database COMMAND Database_CreateTest)

add_subdirectory(test)

else()

add_library(${ProjectName} SHARED )


add_library(ark_api STATIC IMPORTED)
set_target_properties(ark_api PROPERTIES
  IMPORTED_LOCATION ${PATH_ARK_API}/out_lib/ArkApi.lib
  INTERFACE_INCLUDE_DIRECTORIES ${PATH_ARK_API}/version/Core/Public
)



add_library(my_sql STATIC IMPORTED)
set_target_properties(my_sql PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Libs/libmysql.lib
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/Libs/mysqlclient.lib
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/Includes/
)


message ("TODO: import to project")
add_library(permissions STATIC IMPORTED)
set_target_properties(permissions PROPERTIES
  IMPORTED_LOCATION ${CMAKE_CURRENT_SOURCE_DIR}/../Permissions/out_lib/Permissions.lib
  INTERFACE_INCLUDE_DIRECTORIES ${CMAKE_CURRENT_SOURCE_DIR}/../Permissions/Permissions/Public/
)



set_target_properties(${ProjectName} PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(${ProjectName} 
PRIVATE
	ark_api
	my_sql  
	permissions)


endif()

set_target_properties( ${ProjectName} PROPERTIES
    CXX_STANDARD 17
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
)

ADD_DEFINITIONS(-D_UNICODE -DARK_GAME -D_SILENCE_CXX17_UNCAUGHT_EXCEPTION_DEPRECATION_WARNING)
add_subdirectory(ArkShop)





macro(GroupSources curdir)
   file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir} ${PROJECT_SOURCE_DIR}/${curdir}/*)
   foreach(child ${children})
          if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
                  GroupSources(${curdir}/${child})
          else()
                  string(REPLACE "/" "\\" groupname ${curdir})
            source_group(${groupname} FILES ${PROJECT_SOURCE_DIR}/${curdir}/${child})
          endif()
   endforeach()
endmacro()
   

GroupSources(ArkShop)