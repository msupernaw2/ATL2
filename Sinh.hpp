/* 
 * File:   Sinh.hpp
 * Author: matthewsupernaw
 *
 * Created on June 18, 2014, 12:48 PM
 */


/**
 *
 * @author  Matthew R. Supernaw
 *
 * Public Domain Notice
 * National Oceanic And Atmospheric Administration
 *
 * This software is a "United States Government Work" under the terms of the
 * United States Copyright Act.  It was written as part of the author's official
 * duties as a United States Government employee and thus cannot be copyrighted.
 * This software is freely available to the public for use. The National Oceanic
 * And Atmospheric Administration and the U.S. Government have not placed any
 * restriction on its use or reproduction.  Although all reasonable efforts have
 * been taken to ensure the accuracy and reliability of the software and data,
 * the National Oceanic And Atmospheric Administration and the U.S. Government
 * do not and cannot warrant the performance warrant the performance or results
 * that may be obtained by using this  software or data. The National Oceanic
 * And Atmospheric Administration and the U.S. Government disclaim all
 * warranties, express or implied, including warranties of performance,
 * merchantability or fitness for any particular purpose.
 *
 * Please cite the author(s) in any work or product based on this material.
 *
 */



#ifndef SINH_HPP
#define SINH_HPP

#include "Expression.hpp"

namespace atl {

    /**
     * Expression template to handle hyperbolic sine for variable or 
     * container expressions. 
     * 
     * \f$  \sinh f(x) \f$
     * 
     * or 
     * 
     * \f$ \sinh f_{i,j}(x)  \f$
     * 
     */
    template<class REAL_T, class EXPR>
    struct Sinh : public ExpressionBase<REAL_T, Sinh<REAL_T, EXPR> > {
        typedef REAL_T BASE_TYPE;

        /**
         * Constructor
         * 
         * @param a
         */
        Sinh(const ExpressionBase<REAL_T, EXPR>& a)
        : expr_m(a.Cast()) {
        }

        /**
         * Computes the hyperbolic sine of the evaluated expression.
         * 
         * @return 
         */
        inline const REAL_T GetValue() const {
            return std::sinh(expr_m.GetValue());
        }

        /**
         * Computes the hyperbolic sine of the evaluated expression at
         * index {i,j}.
         * 
         * @return 
         */
        inline const REAL_T GetValue(size_t i, size_t j = 0) const {
            return std::sinh(expr_m.GetValue(i, j));
        }

        /**
         * Returns true.
         * 
         * @return 
         */
        inline bool IsNonlinear() const {
            return true;
        }

        /**
         * Push variable info into a set.
         *  
         * @param ids
         */
        inline void PushIds(typename atl::StackEntry<REAL_T>::vi_storage& ids)const {
            expr_m.PushIds(ids);
        }

        /**
         * Push variable info into a set at index {i,j}.
         * 
         * @param ids
         * @param i
         * @param j
         */
        inline void PushIds(typename atl::StackEntry<REAL_T>::vi_storage& ids, size_t i, size_t j = 0)const {
            expr_m.PushIds(ids, i, j);
        }

        inline void PushNLIds(typename atl::StackEntry<REAL_T>::vi_storage& ids, bool nl = false)const {
            expr_m.PushNLIds(ids, true);
        }

        inline const std::complex<REAL_T> ComplexEvaluate(uint32_t x, REAL_T h = 1e-20) const {
            return std::sinh(expr_m.ComplexEvaluate(x, h));
        }

        /**
         * Evaluates the first-order derivative with respect to x.
         * 
         * \f$ \cosh f(x)\,\left({{d}\over{d\,x}}\,f(x)\right) \f$
         * 
         * @param x
         * @return 
         */
        inline const REAL_T EvaluateDerivative(uint32_t x) const {
            return expr_m.EvaluateDerivative(x) * std::cosh(expr_m.GetValue());
        }

        /**
         * Evaluates the second-order derivative with respect to x and y at
         * index {i,j}.
         * 
         * \f$ \sinh f(x,y)\,\left({{d}\over{d\,x}}\,f(x,y)\right)\,
         *  \left({{d}\over{d\,y}}\,f(x,y)\right)+\cosh f(x,y)\,
         *  \left({{d^2}\over{d\,x\,d\,y}}\,f(x,y)\right) \f$
         * 
         * @param x
         * @param y
         * @return 
         */
        inline REAL_T EvaluateDerivative(uint32_t x, uint32_t y) const {
            return ((std::sinh(expr_m.GetValue()) * expr_m.EvaluateDerivative(x) * expr_m.EvaluateDerivative(y))
                    + (std::cosh(expr_m.GetValue()) * expr_m.EvaluateDerivative(x, y)));
        }

        /**
         * Evaluates the third-order derivative with respect to x, y, and z.
         * 
         * \f$ \cosh f(x,y,z)\,\left({{d}\over{d\,x}}\,f(x,y,z)\right)
         *  \,\left({{d}\over{d\,y}}\,f(x,y,z)\right)\,\left({{d}\over{d\,
         *  z}}\,f(x,y,z)\right)+\sinh f(x,y,z)\,\left({{d^2}\over{d
         *  \,x\,d\,y}}\,f(x,y,z)\right)\,\left({{d}\over{d\,z}}\,f(
         *  x,y,z)\right)+ \\ \sinh f(x,y,z)\,\left({{d}\over{d\,x}}\,f(
         *  x,y,z)\right)\,\left({{d^2}\over{d\,y\,d\,z}}\,f(x,y,z)\right)
         *  +\sinh f(x,y,z)\,\left({{d^2}\over{d\,x\,d\,z}}\,f(x,y,z
         *  )\right)\,\left({{d}\over{d\,y}}\,f(x,y,z)\right)+\cosh f_{i,j
         *  }(x,y,z)\,\left({{d^3}\over{d\,x\,d\,y\,d\,z}}\,f(x,y,z)
         *  \right) \f$
         * 
         * @param x
         * @param y
         * @param z
         * @return 
         */
        inline REAL_T EvaluateDerivative(uint32_t x, uint32_t y, uint32_t z) const {
            return std::cosh(expr_m.GetValue())*(expr_m.EvaluateDerivative(x))*
                    (expr_m.EvaluateDerivative(y))*(expr_m.EvaluateDerivative(z))
                    + std::sinh(expr_m.GetValue())*(expr_m.EvaluateDerivative(x, y))
                    *(expr_m.EvaluateDerivative(z)) + std::sinh(expr_m.GetValue())
                    *(expr_m.EvaluateDerivative(x))*(expr_m.EvaluateDerivative(y, z))
                    + std::sinh(expr_m.GetValue())*(expr_m.EvaluateDerivative(x, z))
                    *(expr_m.EvaluateDerivative(y)) + std::cosh(expr_m.GetValue())
                    *(expr_m.EvaluateDerivative(x, y, z));
        }

        /**
         * Evaluates the first-order derivative with respect to x at index 
         * {i,j}.
         * 
         * \f$ \cosh f_{i,j}(x)\,\left({{d}\over{d\,x}}\,f_{i,j}(x)\right) \f$
         * 
         * @param x
         * @param i
         * @param j
         * @return 
         */
        inline const REAL_T EvaluateDerivative(uint32_t x, size_t i, size_t j = 0) const {
            return expr_m.EvaluateDerivative(x, i, j) * std::cosh(expr_m.GetValue(i, j));
        }

        /**
         * Evaluates the second-order derivative with respect to x and y at
         * index {i,j}.
         * 
         * \f$ \sinh f_{i,j}(x,y)\,\left({{d}\over{d\,x}}\,f_{i,j}(x,y)\right)\,
         *  \left({{d}\over{d\,y}}\,f_{i,j}(x,y)\right)+\cosh f_{i,j}(x,y)\,
         *  \left({{d^2}\over{d\,x\,d\,y}}\,f_{i,j}(x,y)\right) \f$
         * 
         * @param x
         * @param y
         * @param i
         * @param j
         * @return 
         */
        inline REAL_T EvaluateDerivative(uint32_t x, uint32_t y, size_t i, size_t j = 0) const {
            return ((std::sinh(expr_m.GetValue(i, j)) * expr_m.EvaluateDerivative(x, i, j) * expr_m.EvaluateDerivative(y, i, j))
                    + (std::cosh(expr_m.GetValue(i, j)) * expr_m.EvaluateDerivative(x, y, i, j)));
        }

        /**
         * Evaluates the third-order derivative with respect to x, y, and z at 
         * index {i,j}.
         * 
         * \f$ \cosh f_{i,j}(x,y,z)\,\left({{d}\over{d\,x}}\,f_{i,j}(x,y,z)\right)
         *  \,\left({{d}\over{d\,y}}\,f_{i,j}(x,y,z)\right)\,\left({{d}\over{d\,
         *  z}}\,f_{i,j}(x,y,z)\right)+\sinh f_{i,j}(x,y,z)\,\left({{d^2}\over{d
         *  \,x\,d\,y}}\,f_{i,j}(x,y,z)\right)\,\left({{d}\over{d\,z}}\,f_{i,j}(
         *  x,y,z)\right)+ \\ \sinh f_{i,j}(x,y,z)\,\left({{d}\over{d\,x}}\,f_{i,j}(
         *  x,y,z)\right)\,\left({{d^2}\over{d\,y\,d\,z}}\,f_{i,j}(x,y,z)\right)
         *  +\sinh f_{i,j}(x,y,z)\,\left({{d^2}\over{d\,x\,d\,z}}\,f_{i,j}(x,y,z
         *  )\right)\,\left({{d}\over{d\,y}}\,f_{i,j}(x,y,z)\right)+\cosh f_{i,j
         *  }(x,y,z)\,\left({{d^3}\over{d\,x\,d\,y\,d\,z}}\,f_{i,j}(x,y,z)
         *  \right) \f$
         * 
         * @param x
         * @param y
         * @param z
         * @param i
         * @param j
         * @return 
         */
        inline REAL_T EvaluateDerivative(uint32_t x, uint32_t y, uint32_t z, size_t i, size_t j = 0) const {
            return std::cosh(expr_m.GetValue(i, j))*(expr_m.EvaluateDerivative(x, i, j))*
                    (expr_m.EvaluateDerivative(y, i, j))*(expr_m.EvaluateDerivative(z, i, j))
                    + std::sinh(expr_m.GetValue(i, j))*(expr_m.EvaluateDerivative(x, y, i, j))
                    *(expr_m.EvaluateDerivative(z, i, j)) + std::sinh(expr_m.GetValue(i, j))
                    *(expr_m.EvaluateDerivative(x, i, j))*(expr_m.EvaluateDerivative(y, z, i, j))
                    + std::sinh(expr_m.GetValue(i, j))*(expr_m.EvaluateDerivative(x, z, i, j))
                    *(expr_m.EvaluateDerivative(y, i, j)) + std::cosh(expr_m.GetValue(i, j))
                    *(expr_m.EvaluateDerivative(x, y, z, i, j));
        }

        /**
         * Return the number of rows.
         * 
         * @return 
         */
        size_t GetRows() const {
            return expr_m.GetRows();
        }

        /**
         * True if this expression is a scalar.
         * 
         * @return 
         */
        bool IsScalar() const {
            return expr_m.IsScalar();
        }

        /**
         * Create a string representation of this expression template. 
         * @return 
         */
        const std::string ToExpressionTemplateString() const {
            std::stringstream ss;
            ss << "atl::Sinh<T," << expr_m.ToExpressionTemplateString() << " >";
            return ss.str();
        }


        const EXPR& expr_m;
    };

    /**
     * Creates a expression template representing hyperbolic sine.
     * 
     * @param exp
     * @return 
     */
    template<class REAL_T, class EXPR>
    inline const Sinh<REAL_T, EXPR> sinh(const ExpressionBase<REAL_T, EXPR>& exp) {
        return Sinh<REAL_T, EXPR>(exp.Cast());
    }

}//end namespace atl

#endif
