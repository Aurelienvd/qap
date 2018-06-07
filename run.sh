SEED=$3
INSTANCE=$4
INSTANCE="${INSTANCE##*/}"
shift 4 || exit 1
CONFIG_PARAMS=$*

src/qap --instance $INSTANCE --seed ${SEED} ${CONFIG_PARAMS}