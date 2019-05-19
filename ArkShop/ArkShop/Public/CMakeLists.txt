cmake_minimum_required (VERSION 3.8)


target_include_directories(${ProjectName}
	PRIVATE 
	${CMAKE_CURRENT_SOURCE_DIR}
)

set( SOURCE_FILES

)
set( HEADE_FILES
   ${CMAKE_CURRENT_SOURCE_DIR}/Base.h
   ${CMAKE_CURRENT_SOURCE_DIR}/DBHelper.h
   ${CMAKE_CURRENT_SOURCE_DIR}/ITimedRewards.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Kits.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Points.h
   ${CMAKE_CURRENT_SOURCE_DIR}/Store.h
)

target_sources(${ProjectName}
    PUBLIC
		${SOURCE_FILES}
	PUBLIC
		${HEADE_FILES}
)

