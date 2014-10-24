MRuby::Gem::Specification.new('mruby-chipmunk2d') do |spec|
  spec.license = 'MIT'
  spec.authors = ['Corey Powell']
  spec.version = '7.0.0.0'
  spec.summary = 'Chipmunk2d bindings'
  spec.description = 'Chipmunk2d mruby bindings'
  spec.homepage = 'https://github.com/IceDragon200/mruby-chipmunk2d'

  spec.cc.include_paths << ["#{build.root}/src"]
  spec.cc.flags << '-Werror'
end
