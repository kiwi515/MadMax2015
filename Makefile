.PHONY: default
default: help

# Docker information
DOCKER_TAG       := mm-image
DOCKER_VERSION   ?= latest
DOCKER_CONTAINER := mm  # Must match docker_container in the project YAML!
DOCKER_WORKDIR   := /mm # Must match WORKDIR in the Dockerfile!

# ============================================================================#
# Split the game executable with ELFSplit
# ============================================================================#
.PHONY: split
split:
# TODO(kiwi) Im lazy :(
	@echo "Not implemented!"

# ============================================================================#
# Starts up the MM decomp Docker container
# ============================================================================#
.PHONY: run
run:
# Release old container if it exists
	docker stop $(DOCKER_CONTAINER) && docker rm $(DOCKER_CONTAINER) || true

# Mount the repository source code & tools
	docker run --detach --tty \
		--name $(DOCKER_CONTAINER) \
		--mount type=bind,src="$(shell pwd)",dst=$(DOCKER_WORKDIR) \
		$(DOCKER_TAG):$(DOCKER_VERSION)

# Re-run the latest configure script.
# Can't do this in the Dockerfile because the bind mount is too late!
	docker exec $(DOCKER_CONTAINER) python3 ./configure.py

# Build the latest Clangd compile commands
	python ./tools/ninja/make_compile_cmds.py

# ============================================================================#
# Pulls the latest MM decomp Docker image
# ============================================================================#
.PHONY: docker-pull
docker-pull:
# TODO(kiwi) We need to push the Docker image somewhere
	@echo "Not implemented!"

# ============================================================================#
# Builds the MM decomp Docker image locally
# ============================================================================#
.PHONY: docker-build
docker-build:
	docker build \
		. \
		-t $(DOCKER_TAG):$(DOCKER_VERSION)

# ============================================================================#
# Help display
# ============================================================================#
.PHONY: help
help:
	@echo "==================================================================="
	@echo "Available Make targets:                                            "
	@echo "==================================================================="
	@echo "split:                    Split the game executable with ELFSplit  "
	@echo "run:                      Starts up the MM decomp Docker container "
	@echo "docker-pull:              Pulls the latest MM decomp Docker image  "
	@echo "docker-build:             Builds the MM decomp Docker image locally"
