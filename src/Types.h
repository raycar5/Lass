#pragma once
#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Value.h>
#include <string>

namespace lass {
class LassValue {
public:
  virtual ~LassValue() {}
  virtual void codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const = 0;
  virtual std::string print(bool pretty) const = 0;
};

class LassLong : public LassValue {
public:
  explicit LassLong(long value) : value(value) {}
  virtual void codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const override;
  virtual std::string print(bool pretty) const override {
    return "Long:" + std::to_string(value);
  }

private:
  long value;
};
class LassSymbol : public LassValue {
public:
  explicit LassSymbol(std::string name) : name(name) {}

  virtual void codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const override;
  virtual std::string print(bool pretty) const override {
    return "Symbol:" + name;
  }

private:
  std::string name;
};
class LassList : public LassValue {
public:
  void add(std::unique_ptr<LassValue> value) {
    list.push_back(std::move(value));
  }
  LassValue *get(size_t index) { return list[index].get(); }
  virtual std::string print(bool pretty) const override {
    std::string s = "List:(";
    for (size_t i = 0; i < list.size(); ++i) {
      s += list[i]->print(pretty) + " ";
    }
    return s + ")";
  }
  virtual void codegen(llvm::LLVMContext context,
                       llvm::IRBuilder<> builder) const override;

private:
  std::vector<std::unique_ptr<LassValue>> list;
};

} // namespace lass
