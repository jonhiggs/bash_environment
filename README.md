# bash_environment

Persist environment variables across shell sessions.


## Usage

It works similar to the `export` builtin.

* Writing: `bash_environment key=value`
* Reading: `bash_environment key`
* Listing: `bash_environment`


## Caveats

This works by writing variables into a file at `${HOME}/.bash_environment`, which needs to be sourced into each environment upon any change. This functionality is not provided.

