MRuby::Build.new do |conf|
  toolchain :gcc
  conf.gembox 'default'

  conf.gem '.'

  chipmunk_dir = ENV['CHIPMUNK_DIRNAME']
  conf.cc do |cc|
    cc.include_paths << File.join(chipmunk_dir, 'include')
  end

  conf.linker do |linker|
    linker.library_paths << File.join(chipmunk_dir, 'build/src')
    linker.libraries << 'chipmunk_static'
  end
end
