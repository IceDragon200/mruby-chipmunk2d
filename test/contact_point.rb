assert('Chipmunk2d::ContactPoint type') do
  assert_kind_of(Class, Chipmunk2d::ContactPoint)
end

assert('Chipmunk2d::ContactPointSet type') do
  assert_kind_of(Class, Chipmunk2d::ContactPointSet)
end

assert('Chipmunk2d::ContactPoint#initialize') do
  cps = Chipmunk2d::ContactPoint.new
  assert_kind_of(Chipmunk2d::ContactPoint, cps)
end

assert('Chipmunk2d::ContactPoint#point_a') do
  contact_point = Chipmunk2d::ContactPoint.new
  assert_kind_of(Chipmunk2d::Vect, contact_point.point_a)
end

assert('Chipmunk2d::ContactPoint#point_b') do
  contact_point = Chipmunk2d::ContactPoint.new
  assert_kind_of(Chipmunk2d::Vect, contact_point.point_b)
end

assert('Chipmunk2d::ContactPoint#distance') do
  contact_point = Chipmunk2d::ContactPoint.new
  assert_kind_of(Float, contact_point.distance)
end

assert('Chipmunk2d::ContactPointSet#initialize') do
  cps = Chipmunk2d::ContactPointSet.new
  assert_kind_of(Chipmunk2d::ContactPointSet, cps)
end

assert('Chipmunk2d::ContactPointSet#count') do
  cps = Chipmunk2d::ContactPointSet.new
  assert_kind_of(Integer, cps.count)
end

assert('Chipmunk2d::ContactPointSet#normal') do
  cps = Chipmunk2d::ContactPointSet.new
  assert_kind_of(Chipmunk2d::Vect, cps.normal)
end

assert('Chipmunk2d::ContactPointSet#points') do
  cps = Chipmunk2d::ContactPointSet.new
  assert_kind_of(Array, cps.points)
end
