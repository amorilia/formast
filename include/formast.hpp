#ifndef FORMAST_HPP_INCLUDED
#define FORMAST_HPP_INCLUDED

#ifdef FORMAST_STATIC
// formast static library
#  define FORMAST_API
#  define FORMAST_HIDDEN
#else
// formast shared library
#  if defined _WIN32 || defined __CYGWIN__
// Windows
#    ifdef formastlib_EXPORTS
// formast is being compiled: export API to dll
#      define FORMAST_API __declspec(dllexport)
#    else
// other code is being compiled, using formast.dll: import API from dll
#      define FORMAST_API __declspec(dllimport)
#    endif
#    define FORMAST_HIDDEN
#  elif __GNUC__ >= 4
// GNU Linux: set visibility of symbols
#    define FORMAST_API    __attribute__ ((visibility ("default")))
#    define FORMAST_HIDDEN __attribute__ ((visibility ("hidden")))
#  else
// unknown
#    define FORMAST_API
#    define FORMAST_HIDDEN
#  endif
#endif

#include <boost/cstdint.hpp>
#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>
#include <string>
#include <vector>

#include "formast/detail/ast.hpp"

namespace formast
{

typedef formast::detail::ast::Top Top;
typedef formast::detail::ast::Stats Stats;
typedef formast::detail::ast::Expr Expr;

typedef std::string Doc;

struct Attr {
    std::string class_name;
    std::string name;
    boost::optional<Doc> doc;
};

struct Class {
    std::string name;
    boost::optional<std::string> base_name;
    boost::optional<Doc> doc;
    boost::optional<Stats> stats;
};

struct If {
    Expr expr;
    Stats then;
    boost::optional<Stats> else_;
};

class Parser
{
public:
    FORMAST_API Parser();
    FORMAST_API virtual void parse_stream(std::istream & is, Top & top) = 0;
    FORMAST_API void parse_string(std::string const & s, Top & top);
};

class XmlParser : public Parser
{
public:
    FORMAST_API XmlParser();
    FORMAST_API virtual void parse_stream(std::istream & is, Top & top);
};

class Visitor
{
public:
    FORMAST_API Visitor();
    FORMAST_API virtual ~Visitor();

    FORMAST_API virtual void top(Top const & top);
    FORMAST_API virtual void top_class(Class const & class_);

    FORMAST_API virtual void stats(Stats const & stats);
    FORMAST_API virtual void stats_attr(Attr const & attr);
    FORMAST_API virtual void stats_if(If const & if_);

    FORMAST_API virtual void expr(Expr const & e);
    FORMAST_API virtual void expr_uint(boost::uint64_t const & n);
    FORMAST_API virtual void expr_id(std::string const & i);
    FORMAST_API virtual void expr_pos(Expr const & right);
    FORMAST_API virtual void expr_neg(Expr const & right);
    FORMAST_API virtual void expr_add(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_sub(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_mul(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_div(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_mod(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_pow(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_logical_and(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_logical_or(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_logical_not(Expr const & right);
    FORMAST_API virtual void expr_bitwise_and(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_bitwise_or(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_bitwise_xor(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_eq(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_ne(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_gt(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_lt(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_ge(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_compare_le(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_shift_left(Expr const & left, Expr const & right);
    FORMAST_API virtual void expr_shift_right(Expr const & left, Expr const & right);
private:
    // pimpl idiom
    FORMAST_HIDDEN class ExprVisitor;
    boost::shared_ptr<ExprVisitor> _expr_visitor;
    FORMAST_HIDDEN class TopVisitor;
    boost::shared_ptr<TopVisitor> _top_visitor;
    FORMAST_HIDDEN class StatsVisitor;
    boost::shared_ptr<StatsVisitor> _stats_visitor;
};

} // namespace formast

#endif
