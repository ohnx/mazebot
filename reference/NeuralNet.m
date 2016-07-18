% simple neural network
% by: Mason X et al.
classdef NeuralNet
	properties
        nodes
        % negative numbers are the input values. ie, -1 is value w/ index 1
        % zero is output
        % other numbers are index values
        nodeconnections
        %this network is not reccurrent
	end
    methods
        function obj = NeuralNet(nodes)
            obj.nodes = nodes;
            obj.nodeconnections = [];
        end
        function nn = addNode(nn, node)
            nn.nodes = [nn.nodes node];
        end
        function nn = addConnection(nn, ia, ib)
            max = length(nn.nodes);
            if ia > max || ib > max
                error('Invalid node id');
            end
            nn.nodeconnections = [nn.nodeconnections [ia ib]];
        end
        function results = runNeuralNet(nn, input)
            nodedata = {};
            % outputs is a list of nodes that 0 (aka output) rely on
            outputs = [];
            % no support for recurrent
            storedvalues = zeros(1, length(nn.nodes));
            % calculated values
            calculatedvalues = zeros(1, length(nn.nodes));
            
            % stick everything in the format <element> relies on <elements>
            for i = 1:length(nn.nodeconnections)
                nodeconnect = nn.nodeconnections(i);
                if nodeconnect(2) == 0
                    outputs = [outputs nodeconnect(1)];
                    continue
                end
                nodedatatemp = nodedata{nodeconnect(2)};
                if isempty(nodedatatemp)
                    nodedata{nodeconnect(2)} = [];
                end
                nodedatatemp = [nodedatatemp nodeconnect(1)];
                nodedata{nodeconnect(2)} = nodedatatemp;
            end
            
            dontuse = 0;
            % process the nodes with no other nodes needed
            for i = 1:length(nodedata)
                lst = nodedata{i};
                for j = 1:length(lst)
                    if lst(j) > 0
                        dontuse = 1;
                        break
                    end
                end
                if dontuse
                    dontuse = 0;
                    continue
                end
                % this is all negative numbers
                % build the list of input values
                deps = zeros(1, length(lst));
                for j = 1:length(lst)
                    deps(j) = input(abs(lst(j)));
                end
                storedvalues(1,i) = calcSigmoidNeuron(nn.nodes(i), deps);
            end
            
            didProcess = 1;
            %process nodes that have stuff
            while didProcess
                didProcess = 0;
                for i = 1:length(nodedata)
                    %check if value already calculated
                    if calculatedvalues(i)
                        continue
                    end
                    % check all dependencies satisfied
                    doProcess = 1;
                    for j = 1:length(nodedata{i})
                        if nodedata{i}(j) > 0 && calculatedvalues(nodedata{i}(j)) == 0
                            doProcess = 0;
                            break
                        end
                    end
                    if doProcess == 0
                        continue
                    end
                    % build the list of input values
                    deps = zeros(1, length(lst));
                    for j = 1:length(lst)
                        deps(j) = input(abs(lst(j)));
                    end
                    storedvalues(1,i) = calcSigmoidNeuron(nn.nodes(i), deps);
                    calculatedvalues(i) = 1;
                    didProcess = 1;
                end
            end
            
            %save results
            results = zeros(1, length(outputs));
            for i = 1:length(outputs)
                results(i) = storedvalues(outputs(i));
            end
        end
        function newnet = mateNeuralNet(a, b, threshold)
            if nargin < 3
                threshold = 0.51337;
            end
            if length(a.nodes) ~= length(b.nodes)
                error('Incompatible parents');
            end
            if length(a.nodeconnections) ~= length(b.nodeconnections)
                error('Mating node connections is not supported.');
            end
            newnet = NeuralNet(a.nodes);
            newnet.nodeconnections = a.nodeconnections;
            for i = 1:length(a.nodes)
                newnet.nodes(i) = mateSigmoidNeuron(a.nodes(i), b.nodes(i), threshold);
            end
            % node connections are not changed
        end
        function newnet = mutateNeuralNet(nn, threshold)
            newnet = NeuralNet(a.nodes);
            newnet.nodeconnections = nn.nodeconnections;
            for i = 1:length(nn.nodes)
                newnet.nodes(i) = mutateSignmoidNeuron(nn.nodes(i), threshold);
            end
        end
    end
end