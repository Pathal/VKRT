#pragma once

/*
Vertex layout components
*/
typedef enum Component {
	VERTEX_COMPONENT_POSITION = 0x0,
	VERTEX_COMPONENT_NORMAL = 0x1,
	VERTEX_COMPONENT_COLOR = 0x2,
	VERTEX_COMPONENT_UV = 0x3,
	VERTEX_COMPONENT_TANGENT = 0x4,
	VERTEX_COMPONENT_BITANGENT = 0x5,
	VERTEX_COMPONENT_DUMMY_FLOAT = 0x6,
	VERTEX_COMPONENT_DUMMY_VEC4 = 0x7
} Component;


/*
Ray Tracing
*/
typedef enum VkRayTracingShaderGroupTypeNV {
	VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV = 0,
	VK_RAY_TRACING_SHADER_GROUP_TYPE_TRIANGLES_HIT_GROUP_NV = 1,
	VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV = 2,
	VK_RAY_TRACING_SHADER_GROUP_TYPE_BEGIN_RANGE_NV = VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV,
	VK_RAY_TRACING_SHADER_GROUP_TYPE_END_RANGE_NV = VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV,
	VK_RAY_TRACING_SHADER_GROUP_TYPE_RANGE_SIZE_NV = (VK_RAY_TRACING_SHADER_GROUP_TYPE_PROCEDURAL_HIT_GROUP_NV - VK_RAY_TRACING_SHADER_GROUP_TYPE_GENERAL_NV + 1),
	VK_RAY_TRACING_SHADER_GROUP_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkRayTracingShaderGroupTypeNV;

typedef enum VkGeometryTypeNV {
	VK_GEOMETRY_TYPE_TRIANGLES_NV = 0,
	VK_GEOMETRY_TYPE_AABBS_NV = 1,
	VK_GEOMETRY_TYPE_BEGIN_RANGE_NV = VK_GEOMETRY_TYPE_TRIANGLES_NV,
	VK_GEOMETRY_TYPE_END_RANGE_NV = VK_GEOMETRY_TYPE_AABBS_NV,
	VK_GEOMETRY_TYPE_RANGE_SIZE_NV = (VK_GEOMETRY_TYPE_AABBS_NV - VK_GEOMETRY_TYPE_TRIANGLES_NV + 1),
	VK_GEOMETRY_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkGeometryTypeNV;

typedef enum VkAccelerationStructureTypeNV {
	VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV = 0,
	VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV = 1,
	VK_ACCELERATION_STRUCTURE_TYPE_BEGIN_RANGE_NV = VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV,
	VK_ACCELERATION_STRUCTURE_TYPE_END_RANGE_NV = VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV,
	VK_ACCELERATION_STRUCTURE_TYPE_RANGE_SIZE_NV = (VK_ACCELERATION_STRUCTURE_TYPE_BOTTOM_LEVEL_NV - VK_ACCELERATION_STRUCTURE_TYPE_TOP_LEVEL_NV + 1),
	VK_ACCELERATION_STRUCTURE_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkAccelerationStructureTypeNV;

typedef enum VkCopyAccelerationStructureModeNV {
	VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV = 0,
	VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV = 1,
	VK_COPY_ACCELERATION_STRUCTURE_MODE_BEGIN_RANGE_NV = VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV,
	VK_COPY_ACCELERATION_STRUCTURE_MODE_END_RANGE_NV = VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV,
	VK_COPY_ACCELERATION_STRUCTURE_MODE_RANGE_SIZE_NV = (VK_COPY_ACCELERATION_STRUCTURE_MODE_COMPACT_NV - VK_COPY_ACCELERATION_STRUCTURE_MODE_CLONE_NV + 1),
	VK_COPY_ACCELERATION_STRUCTURE_MODE_MAX_ENUM_NV = 0x7FFFFFFF
} VkCopyAccelerationStructureModeNV;

typedef enum VkAccelerationStructureMemoryRequirementsTypeNV {
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV = 0,
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BUILD_SCRATCH_NV = 1,
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV = 2,
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_BEGIN_RANGE_NV = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV,
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_END_RANGE_NV = VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV,
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_RANGE_SIZE_NV = (VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_UPDATE_SCRATCH_NV - VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_OBJECT_NV + 1),
	VK_ACCELERATION_STRUCTURE_MEMORY_REQUIREMENTS_TYPE_MAX_ENUM_NV = 0x7FFFFFFF
} VkAccelerationStructureMemoryRequirementsTypeNV;


typedef enum VkGeometryFlagBitsNV {
	VK_GEOMETRY_OPAQUE_BIT_NV = 0x00000001,
	VK_GEOMETRY_NO_DUPLICATE_ANY_HIT_INVOCATION_BIT_NV = 0x00000002,
	VK_GEOMETRY_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkGeometryFlagBitsNV;
typedef VkFlags VkGeometryFlagsNV;

typedef enum VkGeometryInstanceFlagBitsNV {
	VK_GEOMETRY_INSTANCE_TRIANGLE_CULL_DISABLE_BIT_NV = 0x00000001,
	VK_GEOMETRY_INSTANCE_TRIANGLE_FRONT_COUNTERCLOCKWISE_BIT_NV = 0x00000002,
	VK_GEOMETRY_INSTANCE_FORCE_OPAQUE_BIT_NV = 0x00000004,
	VK_GEOMETRY_INSTANCE_FORCE_NO_OPAQUE_BIT_NV = 0x00000008,
	VK_GEOMETRY_INSTANCE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkGeometryInstanceFlagBitsNV;
typedef VkFlags VkGeometryInstanceFlagsNV;

typedef enum VkBuildAccelerationStructureFlagBitsNV {
	VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_UPDATE_BIT_NV = 0x00000001,
	VK_BUILD_ACCELERATION_STRUCTURE_ALLOW_COMPACTION_BIT_NV = 0x00000002,
	VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_TRACE_BIT_NV = 0x00000004,
	VK_BUILD_ACCELERATION_STRUCTURE_PREFER_FAST_BUILD_BIT_NV = 0x00000008,
	VK_BUILD_ACCELERATION_STRUCTURE_LOW_MEMORY_BIT_NV = 0x00000010,
	VK_BUILD_ACCELERATION_STRUCTURE_FLAG_BITS_MAX_ENUM_NV = 0x7FFFFFFF
} VkBuildAccelerationStructureFlagBitsNV;
typedef VkFlags VkBuildAccelerationStructureFlagsNV;