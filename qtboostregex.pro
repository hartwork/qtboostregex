TEMPLATE = subdirs

library_target.subdir = src

examples_target.subdir = examples
examples_target.depends = library_target

SUBDIRS = \
    library_target \
    examples_target \
