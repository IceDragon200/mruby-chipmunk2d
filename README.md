# mruby-chipmunk2d [![Build Status](https://travis-ci.org/IceDragon200/mruby-chipmunk2d.svg?branch=master)](https://travis-ci.org/IceDragon200/mruby-chipmunk2d)
[Mruby](https://github.com/mruby/mruby) bindings for [Chipmunk2d](https://github.com/slembcke/Chipmunk2D).

WIP

Place the following in your build_config
```ruby
# build_config.rb
MRuby::Build.new do |conf|
  ...

  conf.gem github: 'IceDragon200/mruby-chipmunk2d'

  conf.cc do |cc|
    cc.include_paths += ['/path/to/Chipmunk2D/include']
  end

  conf.linker do |linker|
    linker.library_paths << '/path/to/Chipmunk2D'
    linker.libraries << 'chipmunk2d'
  end

  ...
end
```

## Check List
* [x] Arbiter
* [x] BB
* [x] Body
* [x] Constraint
* [x] DampedRotarySpring  (no torque function, there is no support for void *data)
* [x] DampedSpring        (no torque function, there is no support for void *data)
* [x] GearJoint
* [x] GrooveJoint
* [x] Mat2x2
* [x] PinJoint
* [x] PivotJoint
* [x] PolyShape
* [x] RachetJoint
* [x] RotaryLimitJoint
* [x] Shape
* [x] SimpleMotor
* [x] SlideJoint
* [x] Space
* [ ] SpatialIndex
* [x] Transform
* [x] Vect

mruby does not have a 'mark' function, as of such, instance variables are used
to store instances of the ruby data objects. (Shapes in Spaces)
I haven't started binding the ruby objects together, so the library is unstable
at the moment (random crashes after garbage collection).

## Chipmunk2d
Currently chipmunk2d is expected to be a static library for mruby-chipmunk2d,
(it was convient to build it as static).
However a dynamic library MAY work as well (untested).

## Want to Help?
Feel like helping out with the bindings?
`fork`, `clone`, `binding-branch`, `pull-request`, `get-it-merged`
The faster the bindings are finished, the faster we can test it and have physics
goodness in mruby.

## Docs
```shell
# to generate docs locally
rake docs
```
