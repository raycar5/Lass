#include "Types.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"

using namespace llvm;
using namespace std;
namespace lass {
void LassLong::codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const {};
void LassSymbol::codegen(llvm::LLVMContext context,
                         llvm::IRBuilder<> builder) const {};
void LassList::codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const {};
} // namespace lass
