//
// @author raver119@gmail.com, created on 29/10/17
// @author Yurii Shyrma (iuriish@yahoo.com)
//

#include <op_boilerplate.h>
#if NOT_EXCLUDED(OP_softmax)

#include <ops/declarable/CustomOperations.h>
#include <ops/declarable/helpers/activations.h>

namespace nd4j {
namespace ops {


CONFIGURABLE_OP_IMPL(softmax, 1, 1, true, 0, 0) {
    
    NDArray<T>* input  = INPUT_VARIABLE(0);
    NDArray<T>* output = OUTPUT_VARIABLE(0);
    
    const int rank = input->rankOf();
    const int dim  = block.getIArguments()->size() > 0 ? INT_ARG(0) : rank - 1;

    REQUIRE_TRUE(dim < rank, 0, "SOFTMAX OP: the value of input integer parameter (dimension) must be less than input array rank %i, but got dimension = %i instead !", rank, dim);

    helpers::softmax<T>(*input, *output, dim);

    return Status::OK();
}


CONFIGURABLE_OP_IMPL(softmax_bp, 2, 1, true, 0, 0) {
    
    NDArray<T>* input = INPUT_VARIABLE(0);
    NDArray<T>* gradO = INPUT_VARIABLE(1);
    NDArray<T>* gradI = OUTPUT_VARIABLE(0);    

    const int rank = input->rankOf();
    const int dim  = block.getIArguments()->size() > 0 ? INT_ARG(0) : rank - 1;

    REQUIRE_TRUE(dim < rank, 0, "SOFTMAX_BP OP: the value of input integer parameter (dimension) must be less than input array rank %i, but got dimension = %i instead !", rank, dim);
    
    helpers::softmax<T>(*input, *gradI, dim);

    NDArray<T> sumAlongDim = (*gradI * *gradO).template reduceAlongDims<simdOps::Sum<T>>({dim}, true);
    gradI->assign(*gradI * (*gradO - sumAlongDim));

    return Status::OK();
}


}
}

#endif