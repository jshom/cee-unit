# cee-unit ![badge](https://action-badges.now.sh/jshom/cee-unit?action=ci) ![badge](https://img.shields.io/github/license/jshom/cee-unit)

Little library for C Unit testing; one file [CEEU.h](https://github.com/jshom/cee-unit/blob/master/CEEU.h)

## Usage

For full example, see [./tests/](https://github.com/jshom/cee-unit/tree/master/tests), this project is testing itself... gotta love dogfooding :)

### Quick Start

First, lets make an entrypoint for the tests, lets call it `test.c`.

And then, lets download CEEU.h from a release so that we can reference it in our `test.c` file.

```c
#include "./CEEU.h"

CEEU_test_result* test__is_a_success() {
    // create assertion set
    CEEU_assertions* as = CEEU_assertions(__func__);

    // add assertion to check that 1 == 1
    CEEU_assertions__add(as, CEEU_assert__int_equals(1, 1));

    // return all of our assertions
    return CEEU_assertions__resolve(as);
}

int main() {
    // create driver or a test runner for all of our awesome tests
    CEEU_test_runner* trnr = CEEU_test_runner__new();

    // add a test, or more
    CEEU_test_runner__add_test(trnr, &test__is_a_success);

    // execute all of our tests that we added to the test runner
    return CEEU_test_runner__exec(trnr);
}
```

### Extras

Your project will probably have some special struct's or more elaborate
criteria that you might want to represent with your own assertions. This can be
easily done by appending to the `CEEU.h` file.

Here is an example of adding a new assertion for `CEEU_assert__book_equals`

```c
/* ... standard CEEU.h stuff above ... */

typedef struct {
    int id;
    /* more code... */
} Book;

CEEU_assert CEEU_assert__book_equals(Book* book_a, Book* book_b) {
    char* failure_message = (char*) malloc(CEEU_ASSERTION_MESSAGE_SIZE);
    // use CEEU_ASSERTION_MESSAGE_SIZE_LARGE if you need more space
    
    sprintf(
        failure_message,
        "Failed to assert Book[%d] equals Book[%d]",
        book_a->id,
        book_b->id
    );
    
    // return a new assertion that will only show failure message if check if false
    return CEEU_assert__new(book_a->id == book_b->id, failure_message);
}

```

If you feel like an assertion you write is broadly applicable, please create a PR, thx!

## Two Cents

Highly recommend using clangd so you can get some sweet autocomplete to show all available assertions and functions.

## License

Licensed under GPLv3. Please keep this in public domain, thx!
