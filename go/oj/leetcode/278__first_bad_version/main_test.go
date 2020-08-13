package _78__first_bad_version

import (
	"github.com/stretchr/testify/assert"
	"testing"
)

func Test_78__first_bad_version(t *testing.T) {
	assert.Equal(t, BadVersion, firstBadVersion(1000))
}

