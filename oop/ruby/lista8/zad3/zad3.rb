class Jawna
    def initialize(unencrypted)
        @unencrypted = unencrypted
    end

    def zaszyfruj(key_hash)
        encrypted = @unencrypted.split("").map{ |char| key_hash[char] }.join("")
        Zaszyfrowana.new(encrypted)
    end

    def to_s
        @unencrypted
    end
end

class Zaszyfrowana
    def initialize(encrypted)
        @encrypted = encrypted
    end

    def odszyfruj(key_hash)
        unencrypted = @encrypted.split("").map{ |char| key_hash.key(char) }.join("")
        Jawna.new(unencrypted)
    end

    def to_s
        @encrypted
    end
end

key = {
    'a' => 'b',
    'b' => 'r',
    'r' => 'y',
    'y' => 'u',
    'u' => 'a'
}

puts Jawna.new("ruby").zaszyfruj(key)
puts Zaszyfrowana.new("yaru").odszyfruj(key)