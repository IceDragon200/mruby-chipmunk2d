assert('Chipmunk2d::Vect#initialize') do
  Chipmunk2d::Vect.new(12, 12)
end

assert('Chipmunk2d::Vect#==') do
  vect1 = Chipmunk2d::Vect.new(12, 12)
  vect2 = Chipmunk2d::Vect.new(12, 12)
  vect3 = Chipmunk2d::Vect.new(5, 1)

  assert_equal(vect1, vect2)
  assert_not_equal(vect1, vect3)
end
