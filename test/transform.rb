assert('Chipmunk2d::Transform type') do
  assert_kind_of(Class, Chipmunk2d::Transform)
end

assert('Chipmunk2d::Transform#initialize') do
  transform = Chipmunk2d::Transform.new(1.0, 1.0, 0.5, 0.6, 0.2, 0.5)
  assert_kind_of(Chipmunk2d::Transform, transform)
end
