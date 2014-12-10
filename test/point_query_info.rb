assert('Chipmunk2d::PointQueryInfo type') do
  assert_kind_of(Class, Chipmunk2d::PointQueryInfo)
end

assert('Chipmunk2d::PointQueryInfo#initialize [no params]') do
  pqi = Chipmunk2d::PointQueryInfo.new
  assert_kind_of(Chipmunk2d::PointQueryInfo, pqi)
end

assert('Chipmunk2d::PointQueryInfo#initialize') do
  body = Chipmunk2d::Body.new(100, 1)
  shape = Chipmunk2d::CircleShape.new(body, 2, Chipmunk2d::Vect.zero)
  point = Chipmunk2d::Vect.zero
  distance = 2
  gradient = Chipmunk2d::Vect.zero
  pqi = Chipmunk2d::PointQueryInfo.new(shape, point, distance, gradient)
  assert_kind_of(Chipmunk2d::PointQueryInfo, pqi)
end
