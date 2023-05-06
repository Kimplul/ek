# Ek

Ek (oak in Swedish) is my toy programming language.
Currently far from a usable state, but I thought I might
still put it up on GitHub. Get them green squares, yo.

# Building

+ `make`

Add `RELEASE=1` to enable optimizations.

# Ek features and target use case

Ek is inteded to be a simple language, similar to C with little to no runtime but with
some quality of life improvements, mainly stuff already seen in other languages.
Nothing particularly ground-breaking.

# Tests

Tests are currently broken, I'm going to have to come up with some half decent
testing framework.

## Feature showcase

In no particular order of importance or significance.
Check the tests for some more examples.

### C++-style comments
```
// inline comment
/*
 multi line comment
 */
```

Additionally, comments are allowed in comments:
```
/* comment 1
        /* comment2 */
*/
```

### Right to left type declarations
```
// an array of eight pointers to u32
a [8]'u32;
// a pointer to an array of eight u32
b '[8]u32;
```

### Unified function declaration syntax
```
// function definition
some_func(a u8, b u16 => i32){
        // function pointer to some_func
        a_callback '(u8, u16 => i32) = some_func;
}
```

### More legible casts
```
b f32;
a u32 = b as u32;
```

### Immutable by default
```
// immutable i64
a i64 = 32;
// mutable u32
b mut u32 = 32;
```

### Type inference
```
// immutable i64 (integer constants are by default the largest signed type)
a const = 32;
// mutable u32
b mut = 32 as u32;
```

### Strong(er) type system
```
// ERROR
a u32 = 20.0f;
// OK
a u32 = 20.0f as u32;
```

### Defer
```
a const = alloc(16);
defer(dealloc(a));
```

### Shadowing is disallowed
```
a u32;
{
        // ERROR
        a f32;
}
```

Possibly controversial, but I've only ever run into shadowing bugs,
haven't really found it to be a useful feature.

### Function overloading
```
some_func(u32, u64){}
some_func(u32, u32){}
```

### Interfaces
```
// accepts any type, but you're not allowed to do anything with it
typedef any {}
// any type where there exists a function add_one(some_type => some_type)
// fullfills the interface
typedef addable {
        add_one(addable => addable);
}
```

Interfaces are a bit more complex with peculiarities I'm still not entirely sure about,
TODO. For example,
```
typedef some_type {
        add(some_type, some_type => some_type)
}

// does this fullfill some_type for u32 and u64? Or neither?
add(u32, u32 => u64){}
```

These could be fairly easily solved with some extra syntax, but I would really prefer
keeping function syntax in the top context without extra decorations. Maybe just me.
However, as long as I pick an interpretation and stick to it, should be fine.

### Generics through interfaces
```
struct some_struct (A some_interface, B some_other_interface) {
        a T;
        b B;
};
```

Note that each type must implement some interface. Similarly, procedures
can take an interface as the type which makes it 'generic', but type parameters are not
supported:
```
do_something(a some_interface){
// you can only call functions and read members that the interface defines
}
```

This type of interfaces and overloading are tricky to support at the same time, but
I currently use a left-to-right actualization. That is, in each parameter 'index'
there can only be actual types (`u32`, `i64`, `some_struct`), or a fallback 'generic'
interface. Each parameter type is matched to the argument type, and if none of the actual types match,
the fallback is checked. If it also fails, no function implements the requested types.

This is to avoid cases where two interfaces would both be implemented by a type, leading
to unambiguous function resolutions. This system is inherently less powerful than what
C++ for example has, but might be more flexible than Rust, for example.

### Hidden by default
```
// visible through import
pub some_func(){}
// not visible through import
some_other_func(){}
```

### Public imports
```
// visible in this file and through import
pub import "some_file.ek";
// only visible in this file
import "some_file.ek";
```

### AST macros
```
define stuff(x, y) {
        x + y;
}

...
// equivalent to a u32 = (200 + 200) as u32;
a u32 = stuff(20, 200) as u32;
```

Having macros is a useful feature, but they should be limited.
Having the macros operate on the AST gives better control, and for example
defining new functions is disallowed.

By default macros are unhygienic, but you can create a new context to make
them hygienic:
```
define hygienic(){
{// this is hygienic}
// this isn't
}
```

### Compile time variadics
```
some_func(a u32, b u32, ...args) {
        // const for is a compiletime loop that iterates over ...args
        const for x : ...args {
                ...
        }
}
```

Macros also support variadics. Macros and functions are in the same space, so
```
// OK, macro that doesn't take arguments
define some_thing(){}
// ERR, an object with matching signature already exists
some_thing(){}
// OK, the same name is used but the signature is different
some_thing(a u32){}
```

# Architecture

At the moment I'm aiming for transpiling Ek to C. I'm hoping that it will be possible
to add other transpilation targets, for example JavaScript.

# Name

Ek is the current name, mainly because I like oaks and didn't seem to step on anyone's toes.
I had a number of names I toyed around with before pushing to GitHub, any mentions of other
names should be disregarded and preferrably fixed.
