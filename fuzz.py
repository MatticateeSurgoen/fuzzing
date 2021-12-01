#!/usr/bin/env	python3
import glob, subprocess, random, time, threading, os, hashlib

# Run one fuzz case with provided input (which is a  byte array)
def fuzz(thr_id: int, inp: bytearray):
	assert isinstance(thr_id, int)
	assert isinstance(inp, bytearray)

	# Write out the input to a temporary file
	tmpfn = f"tmpinput{thr_id}"
	with open(tmpfn, "wb") as fd:
		fd.write(inp)

	# Run objdump until completion
	sp = subprocess.Popen("./objdump", "-x", tmpfn,
		stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)

	ret = sp.wait()

	# assert that the program ran successfully
	if ret != 0:
		print(f"Exited with {ret}")

		if ret == -11:
			# SIGSEGV
			dahash = hashlib.sha256(inp).hexdigest()
			open(os.path.join("crashes", f"crash_{dahash:64}"), "wb").write(inp)

# Get a listing of all the files in the corpus
# The corpus is the set of files which we pre-seeded the fuzzers with to
# give it valid inputs.These are files that the program should be able to handle
# parsing, that we will ultimately mutate and splice together to try to find
# bugs!
corpus_files = glob.glob("corpus/*")

# Load the corpus files into memory
corpus = set()

for filename in corpus_files:
	corpus.add(open(filename, "rb").read())

# Convert the corpus back into a list as we're done with the set for deduping
# inputs which were not unique
corpus = list(map(bytearray, corpus))

# Get the time at the start of the fuzzer
start = time.time()

# total number of fuzz cases
cases = 0
def worker(thr_id):
	global start, corpus, cases
	while True:
		# Create a copy of an existing input from the corpus
		inp = bytearray(random.choice(corpus))

		for _ in range(random.randint(1, 8)):
			inp[random.randint(0, len(inp))] = random.randint(0, 255)

		# Pick a random input from our corpus
		fuzz(int(thr_id), bytearray(inp))

		# Update number of fuzz cases
		cases += 1

		# Determine the amount of seconds we have been fuzzing for
		elapsed = time.time() - start

		# Determine the number of fuzz cases per seconds
		fcps = float(cases) / elapsed

		print(f"[{elapsed:10.4f}] cases {cases:10} | fcps {fcps:10.4f}")


for thr_id in range(1):
	threading.Thread(target=worker, args[thr_id]).start()

while threading.active.count() > 0:
	time.sleep(0.1)
