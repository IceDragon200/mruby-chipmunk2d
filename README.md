# mruby-chipmunk2d
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
* [x] Arbiter             (needs iv bindings)
* [x] BB                  (needs iv bindings)
* [x] Body                (needs iv bindings)
* [x] Constraint          (needs iv bindings)
* [ ] DampedRotarySpring
* [ ] DampedSpring
* [ ] GearJoint
* [ ] GrooveJoint
* [x] Mat2x2
* [ ] PinJoint
* [ ] PivotJoint
* [ ] PolyShape
* [ ] RachetJoint
* [ ] RotaryLimitJoint
* [ ] Shape               (needs iv bindings)
* [ ] SimpleMotor
* [ ] SlideJoint
* [ ] Space               (currently stubbed out) (needs iv bindings)
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

If you have premake4, you can use this premake4.lua script to build Chipmunk2d
as a static library for mruby-chipmunk2d.
```lua
-- premake4.lua
solution "Chipmunk"
  configurations { "Debug", "Release" }
  location "build"

  project "Chipmunk2d"
    targetname "chipmunk2d"
    kind "StaticLib"
    language "C"
    location "build"
    files {
      "src/*.c"
    }
    includedirs {
      "include",
      "include/chipmunk",
    }
    links {

    }
    libdirs { "lib" }
    buildoptions {
      "-std=gnu99",
      "-Wall"
    }
```
Place the script in the root of your Chipmunk2d copy.

If you don't feel like installing yet another build system, you can try
your luck with the existing build scripts
(cmake didn't work for me, hence the premake4)

## Want to Help?
Feel like helping out with the bindings?
`fork`, `clone`, `binding-branch`, `pull-request`, `get-it-merged`
The faster the bindings are finished, the faster we can test it and have physics
goodness in mruby.
