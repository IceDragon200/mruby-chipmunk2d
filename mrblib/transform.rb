module Chipmunk2d
  class Transform
    # @return [String]
    def inspect
      # format isn't apart of the core mruby implementation, so I'll just
      # leave the id unconverted
      "<#{self.class}:#{__id__} a=#{a} b=#{b} c=#{c} d=#{d} tx=#{tx} ty=#{ty}>"
    end
  end
end
