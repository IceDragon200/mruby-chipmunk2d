assert('Chipmunk2d::Body type') do
  assert_kind_of(Class, Chipmunk2d::Body)
end

assert('Chipmunk2d::Body#initialize') do
  body = Chipmunk2d::Body.new(100, 1)
  assert_kind_of(Chipmunk2d::Body, body)
  assert_equal(body.mass, 100)
  assert_equal(body.moment, 1)
end
