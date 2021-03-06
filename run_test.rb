#!/usr/bin/env ruby
#
# mrbgems test runner
# Copied from mruby-regexp-pcre

gemname = File.basename(File.dirname(File.expand_path __FILE__))

if __FILE__ == $0
  build_chipmunk2d = lambda do
    repository, dir = 'https://github.com/IceDragon200/Chipmunk2d.git', 'tmp/Chipmunk2d'
    build_args = ['-DBUILD_DEMOS=OFF']

    Dir.mkdir 'tmp'  unless File.exist?('tmp')
    unless File.exist?(dir)
      system "git clone --depth=1 #{repository} #{dir}"
    end

    system(%Q(cd #{dir}; mkdir -p build && cd build && cmake .. #{build_args.join(' ')} && make))
  end

  build_mruby = lambda do
    repository, dir = 'https://github.com/mruby/mruby.git', 'tmp/mruby'
    build_args = ARGV
    build_args = ['all', 'test']  if build_args.nil? or build_args.empty?

    Dir.mkdir 'tmp'  unless File.exist?('tmp')
    unless File.exist?(dir)
      system "git clone --depth=1 #{repository} #{dir}"
    end

    chipmunk2d_dir = File.expand_path('tmp/Chipmunk2d')
    config_file = File.expand_path('travis_config.rb', File.dirname(__FILE__))
    system(%Q[cd #{dir}; CHIPMUNK_DIRNAME="#{chipmunk2d_dir}" MRUBY_CONFIG=#{config_file} ruby minirake #{build_args.join(' ')}])
  end

  status1 = build_chipmunk2d.call
  exit status1 unless status1
  status2 = build_mruby.call
  exit status2
end
