MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'

  conf.gem '.'

  conf.cc do |cc|
    cc.include_paths << 'tmp/Chipmunk2D/include'
  end

  conf.linker do |linker|
    linker.library_paths << 'tmp/Chipmunk2D/lib'
    linker.libraries << 'chipmunk2d_static'
  end
end
