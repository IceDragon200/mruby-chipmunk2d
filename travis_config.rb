MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'

  conf.gem '.'

  chipmunk_dir = ENV['CHIPMUNK2D_DIR']
  conf.cc do |cc|
    cc.include_paths << File.join(chipmunk_dir, 'include')
  end

  conf.linker do |linker|
    linker.library_paths << File.join(chipmunk_dir, 'lib')
    linker.libraries << 'chipmunk2d_static'
  end
end
