*# Element and condition indices. We renumber them so each type is numbered from one.
*set var ielem=0
*set var icond=0
Begin ModelPartData
//  VARIABLE_NAME value
End ModelPartData

Begin Properties 0
End Properties

*# Property blocks

Begin Nodes
*#// id	  X	Y	Z
*loop nodes
*format "%i%10.5e%10.5e%10.5e"
*nodesnum	*NodesCoord(1)	*NodesCoord(2)	*NodesCoord(3)
*end nodes
End Nodes

*# Element blocks

*# Condition Blocks

*# Nodal Variable blocks

*# Elemental Variable blocks

*# Conditional Variable blocks
