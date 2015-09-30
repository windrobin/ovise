## Design ##

  * Write minimal interfaces. Only add convenience methods (as members) if access to private members gives a significant advantage. In general, interfaces should do not much more than maintain data-type invariants.
  * To make an interface more convenient, add helper non-friend non-member functions and facades. This helps to reduce coupling tremendously.

## Code ##

Code conventions are not do-or-die strict. They should be adhered to, but can be ignored if the circumstance demands it. Use common sense here! Also, code guidelines were not actually always implemented in the existing code base. When touching a file, try to repair glitches - but again: use common sense, as the ignorance might have been deliberate.

  * Reference and pointer tags go with the type, not with the variable name, i.e. _MyType`*` Var_ instead of _MyType `*`Var_. Only ever declare one variable per statement when using pointers or references.
  * Curly parentheses always stand on their own line (No Java style).
    * There are notable exceptions: when they **directly** follow a keyword, like do and try, when they open a namespace (in which case there is also no indentation), an array data definition or a lambda.
  * Avoid using long qualified type identifiers in variable definitions/declarations. Either typedef the identifier, use the auto keyword or try to circumvent them, e.g., by using BOOST\_FOREACH instead of an iterator based loop.
  * Do not use auto if the variable is a known integral type, such as int or size\_t.
  * Lines should be no longer than 120 characters. Use the guidelines feature in the Productivity Power Tools to help with this.
  * '''Do not''' use #pragma once, use explicit include guards of the form `OVISE_<name-of-source-file-with-module-in-caps-and-underscores>` instead.
  * Functions and variables should use a CamelCase naming scheme
    * Very generic functions or functors may optionally use _names\_like\_this_.
    * Member variables may optionally use an m (not m`_`) prefix, but that must be consistent across a class and such a class cannot contain public or protected variables.
  * Public classes use a C<CamelCaseName> naming scheme.
  * Prefer FOREACH over for, for over while, while over do..while and avoid goto for control flow.

### Conditionals ###
It's okay not to use parentheses with if ... else constructs. However, be symmetric there: If the if part has parentheses, so should the else part, and vice versa.

### Local code ###
Prefer unnamed namespaces or function-local classes/functions over private functions whenever it is reasonable. Do not indent in unnamed namespaces. End the namespace with a comment like this:

```
namespace {

// Private stuff

} // namespace
```

### Pick meaningful variable names ###
Pick names that reflect the semantics of a variable, not its syntax (type etc.,). Avoid type tags, unless the type is very significant in the context of the variable (E.g., if there is the original object and a pointer to this object, it is okay to call the pointer `<NameOfObject>`Ptr). For for-loop indices or variables, where the actual container is meaningful, bare indices like i,j,k,l can and should be used.

### Write flat code ###
Do not nest branching code more than 2 or 3 levels (hence avoid indentation!). If that happens, it is probably a good indicator to write a function. Also, prefer to keep the "main path of execution" the flattest, e.g.:
```
for (int i=0; i<10; ++i)
{
  if (!SomeLikelyCondition)
    continue;
  
  /* Lots of code here..
  ...
  */
}
```
instead of
```
for (int i=0; i<10; ++i)
{
  if (SomeLikelyCondition)
  {  
    /* Lots of code here..
    ...
    */
  }
}
```

## Comments ##
  * Write doxygen comments in multi-line style.
  * Comments for public and protected functions go into the header files. The main goal here is to make such functions useable without looking at the source.
  * Comments for private functions go into the source file.
  * Example:
```
/** Brief description.
    Continue with some more information
    \param a Does something a'ish
    \returns
*/
```