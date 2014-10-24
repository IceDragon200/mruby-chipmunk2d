assert('Chipmunk2d::Space#initialize') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Chipmunk2d::Space, space)
end
