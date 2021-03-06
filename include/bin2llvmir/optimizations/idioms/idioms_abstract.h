/**
 * @file include/bin2llvmir/optimizations/idioms/idioms_abstract.h
 * @brief Instruction idioms analysis abstract class
 * @copyright (c) 2017 Avast Software, licensed under the MIT license
 */

#ifndef BIN2LLVMIR_OPTIMIZATIONS_IDIOMS_IDIOMS_ABSTRACT_H
#define BIN2LLVMIR_OPTIMIZATIONS_IDIOMS_IDIOMS_ABSTRACT_H

#include <llvm/IR/IRBuilder.h>
#include <llvm/IR/Instruction.h>
#include <llvm/IR/Module.h>

#include "bin2llvmir/optimizations/idioms/idioms_types.h"
#include "bin2llvmir/providers/config.h"

namespace bin2llvmir {

/**
 * @brief Instruction idiom analysis abstract class
 */
class IdiomsAbstract {
private:
	CC_arch m_arch;
	CC_compiler m_compiler;
	llvm::Module * m_module;
	Config* m_config = nullptr;

protected:
	IdiomsAbstract();

	void init(llvm::Module * M, Config* c, CC_compiler cc, CC_arch arch);

	CC_compiler getCompiler() const { return m_compiler; }
	CC_arch getArch() const { return m_arch; }
	llvm::Module * getModule() const { return m_module; }
	Config * getConfig() const { return m_config; }

	virtual bool doAnalysis(llvm::Function &, llvm::Pass *) = 0;
	virtual ~IdiomsAbstract() {}

	bool findBranchDependingOn(llvm::BranchInst ** br, llvm::BasicBlock & bb,
		const llvm::Value * val) const;
	static void eraseInstFromBasicBlock(llvm::Value * val, llvm::BasicBlock * bb);
	static bool isPowerOfTwo(unsigned x);
	static bool isPowerOfTwoRepresentable(const llvm::ConstantInt *cnst);
};

} // namespace bin2llvmir

#endif
