//------------------------------------------------------------------------------
// GxB_Matrix_subassign: C(Rows,Cols)<M> = accum (C(Rows,Cols),A) or A'
//------------------------------------------------------------------------------

// SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
// http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

//------------------------------------------------------------------------------

// Compare with GrB_Matrix_assign, which uses M and C_replace differently

// parallel: not here; see GB_subassign_kernel

#include "GB.h"

GrB_Info GxB_Matrix_subassign       // C(Rows,Cols)<M> += A or A'
(
    GrB_Matrix C,                   // input/output matrix for results
    const GrB_Matrix M,             // mask for C(Rows,Cols), unused if NULL
    const GrB_BinaryOp accum,       // accum for Z=accum(C(Rows,Cols),T)
    const GrB_Matrix A,             // first input:  matrix A
    const GrB_Index *Rows,          // row indices
    GrB_Index nRows,                // number of row indices
    const GrB_Index *Cols,          // column indices
    GrB_Index nCols,                // number of column indices
    const GrB_Descriptor desc       // descriptor for C(Rows,Cols), M, and A
)
{ 

    //--------------------------------------------------------------------------
    // check inputs
    //--------------------------------------------------------------------------

    GB_WHERE ("GxB_Matrix_subassign"
        " (C, M, accum, A, Rows, nRows, Cols, nCols, desc)") ;

    GB_RETURN_IF_NULL_OR_FAULTY (C) ;
    GB_RETURN_IF_FAULTY (M) ;
    GB_RETURN_IF_NULL_OR_FAULTY (A) ;

    // get the descriptor
    GB_GET_DESCRIPTOR (info, desc, C_replace, Mask_comp, A_transpose, xx1, xx2);

    //--------------------------------------------------------------------------
    // C(Rows,Cols)<M> = accum (C(Rows,Cols), A) and variations
    //--------------------------------------------------------------------------

    return (GB_subassign (
        C,          C_replace,      // C matrix and its descriptor
        M,          Mask_comp,      // mask matrix and its descriptor
        false,                      // do not transpose the mask
        accum,                      // for accum (C(Rows,Cols),A)
        A,          A_transpose,    // A and its descriptor (T=A or A')
        Rows, nRows,                // row indices
        Cols, nCols,                // column indices
        false, NULL, 0,             // no scalar expansion
        Context)) ;
}

