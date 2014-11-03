assert('Chipmunk2d::BB type') do
  assert_kind_of(Class, Chipmunk2d::BB)
end

assert('Chipmunk2d::BB#initialize') do
  bb = Chipmunk2d::BB.new(1, 1, 1, 1)
  assert_kind_of(Chipmunk2d::BB, bb)
end
