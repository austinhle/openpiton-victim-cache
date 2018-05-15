import sys
import re

PATTERN = "L1\.5: Sending NOC1.*(L15_NOC1_REQTYPE_WRITEBACK_GUARD|" + \
            "L15_NOC1_REQTYPE_LD_REQUEST|L15_NOC1_REQTYPE_ST_UPGRADE_REQUEST|" + \
            "L15_NOC1_REQTYPE_ST_FILL_REQUEST)"

def main(argv):
    if len(argv) != 2:
        print("Please provide the simulation log to parse as an argument.")
        print("Usage: python ../path/to/parser.py ../path/to/sim.log")
        sys.exit(0)

    count = 0

    with open(argv[1], 'r') as file:
        for line in file.readlines():
            match = re.search(PATTERN, line)
            if match:
                count += 1

    print("Number of requests sent from L1.5 to L2 via NOC1: " + str(count))

if __name__ == "__main__":
    main(sys.argv)
