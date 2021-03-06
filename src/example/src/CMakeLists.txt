
# Build examples.
macro(ADDEXEC name src prec)
    #message(STATUS "adding executable ${name} with incdir: ${PASTIX_INCLUDE_DIR_PREC}")
    add_executable(${name} ${src})
    target_link_libraries(${name} pastix ${prec}matrix_driver)
    target_include_directories(${name} PRIVATE
        ${PASTIX_INCLUDE_DIR_PREC}
    )    
endmacro()

macro(ALLEXECS precision)
    if (${precision} STREQUAL notype)
        SET(_precision ${NEUTRAL_PRECISION})
    else()
        SET(_precision ${precision})
    endif()
    ADDEXEC(${precision}simple simple.c ${_precision})
    ADDEXEC(${precision}simple_param simple_param.c ${_precision})
    ADDEXEC(${precision}plot_memory_usage "plot_memory_usage.c;mem_trace.c" ${_precision})
    ADDEXEC(${precision}cppsimple cppsimple.cpp ${_precision})
    if (MPI_FOUND)
        ADDEXEC(${precision}cppsimple_dist cppsimple_dist.cpp ${_precision})
        ADDEXEC(${precision}simple_dist simple_dist.c ${_precision})
        ADDEXEC(${precision}simple_dist_redist simple_dist_redist.c ${_precision})
    endif()
endmacro()

# NoType examples still need an include dir (any)
SETINCDIR(${NEUTRAL_PRECISION})
ALLEXECS(notype)
foreach(prec s d c z)
    if(BUILD_PRECISION MATCHES [${prec}])
        message(STATUS "Generating ${prec}utils.h")
        execute_process(COMMAND sed -f sed_${prec}.in utils.h
            OUTPUT_FILE ${prec}utils.h
            WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
        set_source_files_properties(${prec}utils.h PROPERTIES GENERATED TRUE)
        SETINCDIR(${prec})
        ALLEXECS(${prec})
    endif()
endforeach()

SETINCDIR(${NEUTRAL_PRECISION})
ADDEXEC(schur schur.c ${NEUTRAL_PRECISION})
ADDEXEC(schur2 schur2.c ${NEUTRAL_PRECISION})
ADDEXEC(reentrant reentrant.c ${NEUTRAL_PRECISION})
ADDEXEC(refinement refinement.c ${NEUTRAL_PRECISION})
ADDEXEC(step-by-step step-by-step.c ${NEUTRAL_PRECISION})
ADDEXEC(do_not_redispatch_rhs do_not_redispatch_rhs.c ${NEUTRAL_PRECISION})
ADDEXEC(isolate_zeros isolate_zeros.c ${NEUTRAL_PRECISION})
ADDEXEC(mult-rhs mult-rhs.c ${NEUTRAL_PRECISION})
ADDEXEC(mult-rhs-dist mult-rhs-dist.c ${NEUTRAL_PRECISION})
if (MPI_FOUND)
    ADDEXEC(step-by-step_dist step-by-step_dist.c ${NEUTRAL_PRECISION})
    ADDEXEC(multi-comm multi-comm.c ${NEUTRAL_PRECISION}) 
    ADDEXEC(multi-comm-step multi-comm-step.c ${NEUTRAL_PRECISION})
    # Fortran examples
    add_library(futils OBJECT utils.F90)
    add_dependencies(futils ${NEUTRAL_PRECISION}matrix_driver)
    target_include_directories(futils PRIVATE
        ${PASTIX_INCLUDE_DIR_PREC}
        ${MPI_Fortran_INCLUDE_PATH}
    ) 
    macro(ADDEXECF name src)
        add_executable(${name} ${src} $<TARGET_OBJECTS:futils>)
        target_link_libraries(${name} pastix ${NEUTRAL_PRECISION}matrix_driver MPI::MPI_Fortran)
        target_include_directories(${name} PRIVATE
            ${PASTIX_INCLUDE_DIR_PREC}
        )    
    endmacro()
    ADDEXECF(fstep-by-step fstep-by-step.F90)
    ADDEXECF(fsimple fsimple.F90)
endif()
