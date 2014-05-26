#!/usr/bin/ruby -w

# Function to calculate the byte-wise entropy of a file.
def getByteEntropy(filename)
begin
	contents = IO.binread(filename).split("")
	# Make a histrogram from the array 'contents'
	byte_counters = Hash[*contents.group_by{ |v| v }.flat_map{ |k, v| [k, v.size] }]

	entropy = 0.0
	total_size = contents.length().to_f
	byte_counters.each_value do |count|
		p_i = count / total_size
		entropy -= Math.log2(p_i) * p_i
	end
	return entropy.round(5)

rescue
	# Silently continue
end
end


# Main
ARGV.each do |argv|
	entropy = getByteEntropy(argv)
	if entropy
		puts argv + "\t" + entropy.to_s
	end
end
