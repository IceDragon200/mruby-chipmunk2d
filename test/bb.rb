assert('Chipmunk2d::BB type') do
  assert_kind_of(Class, Chipmunk2d::BB)
end

assert('Chipmunk2d::BB#initialize') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_kind_of(Chipmunk2d::BB, bb)
end

assert('Chipmunk2d::BB#initialize_copy') do
  bb1 = Chipmunk2d::BB.new(1, 1, 1, 1)
  bb2 = bb1.dup
  assert_kind_of(Chipmunk2d::BB, bb2)
  assert_false(bb2.equal?(bb1))
end

assert('Chipmunk2d::BB#l') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_equal(bb.l, 1)
  bb.l = 3
  assert_equal(bb.l, 3)
  assert_equal(bb.b, 1)
  assert_equal(bb.r, 1)
  assert_equal(bb.t, 1)
end

assert('Chipmunk2d::BB#b') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_equal(bb.b, 1)
  bb.b = 3
  assert_equal(bb.l, 1)
  assert_equal(bb.b, 3)
  assert_equal(bb.r, 1)
  assert_equal(bb.t, 1)
end

assert('Chipmunk2d::BB#r') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_equal(bb.r, 1)
  bb.r = 3
  assert_equal(bb.l, 1)
  assert_equal(bb.b, 1)
  assert_equal(bb.r, 3)
  assert_equal(bb.t, 1)
end

assert('Chipmunk2d::BB#t') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_equal(bb.r, 1)
  bb.t = 3
  assert_equal(bb.l, 1)
  assert_equal(bb.b, 1)
  assert_equal(bb.r, 1)
  assert_equal(bb.t, 3)
end

assert('Chipmunk2d::BB#intersects?') do
  bb1 = Chipmunk2d::BB.new(0, 0, 10, 10)
  bb2 = Chipmunk2d::BB.new(9, 9, 15, 15)
  bb3 = Chipmunk2d::BB.new(19, 19, 10, 10)
  assert_true(bb1.intersects?(bb2))
  assert_false(bb1.intersects?(bb3))
end

assert('Chipmunk2d::BB#contains_bb?') do
  bb1 = Chipmunk2d::BB.new(0, 0, 10, 10)
  bb2 = Chipmunk2d::BB.new(9, 9, 10, 10)
  bb3 = Chipmunk2d::BB.new(20, 20, 25, 25)
  assert_true(bb1.contains_bb?(bb2))
  assert_false(bb1.contains_bb?(bb3))
end

assert('Chipmunk2d::BB#merge') do
  bb1 = Chipmunk2d::BB.new(0, 0, 10, 10)
  bb2 = Chipmunk2d::BB.new(9, 9, 20, 13)
  bb3 = bb1.merge(bb2)
  assert_kind_of(Chipmunk2d::BB, bb3)
  assert_equal(0, bb3.l)
  assert_equal(0, bb3.b)
  assert_equal(20, bb3.r)
  assert_equal(13, bb3.t)
end

assert('Chipmunk2d::BB#expand') do
  bb1 = Chipmunk2d::BB.new(0, 0, 10, 10)
  vec = Chipmunk2d::Vect.new(20, 13)
  bb3 = bb1.expand(vec)
  assert_kind_of(Chipmunk2d::BB, bb3)
  assert_equal(0, bb3.l)
  assert_equal(0, bb3.b)
  assert_equal(20, bb3.r)
  assert_equal(13, bb3.t)
end

assert('Chipmunk2d::BB#center') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  vec = bb.center
  assert_kind_of(Chipmunk2d::Vect, vec)
  assert_equal(5, vec.x)
  assert_equal(5, vec.y)
end

assert('Chipmunk2d::BB#area') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  area = bb.area
  assert_kind_of(Float, area)
  assert_equal(100, area)
end

assert('Chipmunk2d::BB#merged_area') do
  bb1 = Chipmunk2d::BB.new(0, 0, 10, 10)
  bb2 = Chipmunk2d::BB.new(3, 5, 15, 18)
  area = bb1.merged_area(bb2)
  assert_kind_of(Float, area)
  assert_equal(270, area)
end

assert('Chipmunk2d::BB#segment_query') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  v1 = Chipmunk2d::Vect.new(2, 5)
  v2 = Chipmunk2d::Vect.new(3, 9)
  result = bb.segment_query(v1, v2)
  assert_kind_of(Float, result)
end

assert('Chipmunk2d::BB#intersects_segment?') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  v1 = Chipmunk2d::Vect.new(2, 5)
  v2 = Chipmunk2d::Vect.new(3, 11)
  v3 = Chipmunk2d::Vect.new(11, 13)
  v4 = Chipmunk2d::Vect.new(14, 14)
  assert_true(bb.intersects_segment?(v1, v2))
  assert_false(bb.intersects_segment?(v3, v4))
end

assert('Chipmunk2d::BB#clamp_vect') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  vect = Chipmunk2d::Vect.new(-1, 11)
  result = bb.clamp_vect(vect)
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_equal(0, result.x)
  assert_equal(10, result.y)
end

assert('Chipmunk2d::BB#wrap_vect') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  vect = Chipmunk2d::Vect.new(-1, 11)
  result = bb.wrap_vect(vect)
  assert_kind_of(Chipmunk2d::Vect, result)
  assert_equal(9, result.x)
  assert_equal(1, result.y)
end

assert('Chipmunk2d::BB#offset') do
  bb = Chipmunk2d::BB.new(0, 0, 10, 10)
  vect = Chipmunk2d::Vect.new(-1, -5)
  result = bb.offset(vect)
  assert_kind_of(Chipmunk2d::BB, result)
  assert_equal(-1, result.l)
  assert_equal(-5, result.b)
  assert_equal(9, result.r)
  assert_equal(5, result.t)
end
