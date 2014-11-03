assert('Chipmunk2d::Space type') do
  assert_kind_of(Class, Chipmunk2d::Space)
end

assert('Chipmunk2d::Space#initialize') do
  space = Chipmunk2d::Space.new
  assert_kind_of(Chipmunk2d::Space, space)
end
