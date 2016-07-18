classdef NeuralNetManager
    properties
        nets
        ratingfunc
        bestNet
        mutateThreshold
        breedThreshold
    end
    methods
        function n = NeuralNetManager(ratingfunc, mutate, breed)
            n.nets = [];
            n.ratingfunc = ratingfunc;
            n.bestNet = 0;
            n.mutateThreshold = mutate;
            n.breedThreshold = breed;
        end
        function ratings = runNeuralNets(nnm, data)
            ratings = zeros(1,length(nnmnets));
            for i = 1:length(nnm.nets)
                ratings(i) = nnm.ratingfunc(nnm.nets(i), data);
                ratings(i,2) = i;
            end
        end
        function nnm = runAndEvolveNeuralNets(nnm, data)
            ratings = runNeuralNets(nnm, data);
            ratings = sortrows(ratings, [-1 2]);
            % pick the two best, breed them a bit, and create a new one
            max = length(n.nets);
            a = nnm.nets(ratings(1,2));
            b = nnm.nets(ratings(2,2));
            for i = 1:max
                nnm.nets(i) = mutateNeuralNet(mateNeuralNet(a, b, nnm.breedThreshold), nnm.mutateThreshold);
            end
            nnm.bestNet = a;
        end
        function nnm = populateNeuralNets(nnm, ref, num)
            nnm.nets = zeros(1, num);
            for i = 1:length(num)
                nnm.nets(i) = NeuralNet(ref.nodes);
                nnm.nets(i).nodeconnections = ref.nodeconnections;
                mutateNeuralNet(nnm.nets(i));
            end
        end
    end
end